#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wmi_device {int /*<<< orphan*/  dev; } ;
struct key_entry {int code; int /*<<< orphan*/  type; } ;
struct dell_wmi_priv {TYPE_3__* input_dev; } ;
struct dell_dmi_results {int err; int keymap_size; struct key_entry* keymap; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_9__ {char* name; TYPE_2__ dev; TYPE_1__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct key_entry*) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KE_END ; 
 struct key_entry* dell_wmi_keymap_type_0000 ; 
 struct key_entry* dell_wmi_keymap_type_0010 ; 
 struct key_entry* dell_wmi_keymap_type_0011 ; 
 struct dell_wmi_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ dmi_walk (int /*<<< orphan*/ ,struct dell_dmi_results*) ; 
 int /*<<< orphan*/  handle_dmi_entry ; 
 scalar_t__ have_scancode (int,struct key_entry*,int) ; 
 TYPE_3__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_3__*) ; 
 int input_register_device (TYPE_3__*) ; 
 struct key_entry* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct key_entry*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int sparse_keymap_setup (TYPE_3__*,struct key_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dell_wmi_input_setup(struct wmi_device *wdev)
{
	struct dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	struct dell_dmi_results dmi_results = {};
	struct key_entry *keymap;
	int err, i, pos = 0;

	priv->input_dev = input_allocate_device();
	if (!priv->input_dev)
		return -ENOMEM;

	priv->input_dev->name = "Dell WMI hotkeys";
	priv->input_dev->id.bustype = BUS_HOST;
	priv->input_dev->dev.parent = &wdev->dev;

	if (dmi_walk(handle_dmi_entry, &dmi_results)) {
		/*
		 * Historically, dell-wmi ignored dmi_walk errors.  A failure
		 * is certainly surprising, but it probably just indicates
		 * a very old laptop.
		 */
		pr_warn("no DMI; using the old-style hotkey interface\n");
	}

	if (dmi_results.err) {
		err = dmi_results.err;
		goto err_free_dev;
	}

	keymap = kcalloc(dmi_results.keymap_size +
			 ARRAY_SIZE(dell_wmi_keymap_type_0000) +
			 ARRAY_SIZE(dell_wmi_keymap_type_0010) +
			 ARRAY_SIZE(dell_wmi_keymap_type_0011) +
			 1,
			 sizeof(struct key_entry), GFP_KERNEL);
	if (!keymap) {
		kfree(dmi_results.keymap);
		err = -ENOMEM;
		goto err_free_dev;
	}

	/* Append table with events of type 0x0010 which comes from DMI */
	for (i = 0; i < dmi_results.keymap_size; i++) {
		keymap[pos] = dmi_results.keymap[i];
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	}

	kfree(dmi_results.keymap);

	/* Append table with extra events of type 0x0010 which are not in DMI */
	for (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0010); i++) {
		const struct key_entry *entry = &dell_wmi_keymap_type_0010[i];

		/*
		 * Check if we've already found this scancode.  This takes
		 * quadratic time, but it doesn't matter unless the list
		 * of extra keys gets very long.
		 */
		if (dmi_results.keymap_size &&
		    have_scancode(entry->code | (0x0010 << 16),
				  keymap, dmi_results.keymap_size)
		   )
			continue;

		keymap[pos] = *entry;
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	}

	/* Append table with events of type 0x0011 */
	for (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0011); i++) {
		keymap[pos] = dell_wmi_keymap_type_0011[i];
		keymap[pos].code |= (0x0011 << 16);
		pos++;
	}

	/*
	 * Now append also table with "legacy" events of type 0x0000. Some of
	 * them are reported also on laptops which have scancodes in DMI.
	 */
	for (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0000); i++) {
		keymap[pos] = dell_wmi_keymap_type_0000[i];
		pos++;
	}

	keymap[pos].type = KE_END;

	err = sparse_keymap_setup(priv->input_dev, keymap, NULL);
	/*
	 * Sparse keymap library makes a copy of keymap so we don't need the
	 * original one that was allocated.
	 */
	kfree(keymap);
	if (err)
		goto err_free_dev;

	err = input_register_device(priv->input_dev);
	if (err)
		goto err_free_dev;

	return 0;

 err_free_dev:
	input_free_device(priv->input_dev);
	return err;
}