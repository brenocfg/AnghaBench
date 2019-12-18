#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ ** groups; int /*<<< orphan*/  release; int /*<<< orphan*/  class; struct device* parent; } ;
struct snd_card {char* private_data; int number; TYPE_1__ card_dev; struct device* dev; int /*<<< orphan*/  irq_descr; int /*<<< orphan*/ ** dev_groups; int /*<<< orphan*/  remove_sleep; int /*<<< orphan*/  power_sleep; int /*<<< orphan*/  files_list; int /*<<< orphan*/  files_lock; int /*<<< orphan*/  ctl_files; int /*<<< orphan*/  controls; int /*<<< orphan*/  ctl_files_rwlock; int /*<<< orphan*/  controls_rwsem; int /*<<< orphan*/  devices; struct module* module; int /*<<< orphan*/  id; } ;
struct module {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  card_dev_attr_group ; 
 int /*<<< orphan*/  check_empty_slot ; 
 char* dev_driver_string (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int get_slot_from_bitmask (int,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_card*) ; 
 int kobject_set_name (int /*<<< orphan*/ *,char*,int) ; 
 struct snd_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_slot_match ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  release_card_device ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 int /*<<< orphan*/  snd_cards_lock ; 
 int snd_ctl_create (struct snd_card*) ; 
 int /*<<< orphan*/  snd_device_free_all (struct snd_card*) ; 
 int snd_ecards_limit ; 
 int snd_info_card_create (struct snd_card*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sound_class ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int snd_card_new(struct device *parent, int idx, const char *xid,
		    struct module *module, int extra_size,
		    struct snd_card **card_ret)
{
	struct snd_card *card;
	int err;

	if (snd_BUG_ON(!card_ret))
		return -EINVAL;
	*card_ret = NULL;

	if (extra_size < 0)
		extra_size = 0;
	card = kzalloc(sizeof(*card) + extra_size, GFP_KERNEL);
	if (!card)
		return -ENOMEM;
	if (extra_size > 0)
		card->private_data = (char *)card + sizeof(struct snd_card);
	if (xid)
		strlcpy(card->id, xid, sizeof(card->id));
	err = 0;
	mutex_lock(&snd_card_mutex);
	if (idx < 0) /* first check the matching module-name slot */
		idx = get_slot_from_bitmask(idx, module_slot_match, module);
	if (idx < 0) /* if not matched, assign an empty slot */
		idx = get_slot_from_bitmask(idx, check_empty_slot, module);
	if (idx < 0)
		err = -ENODEV;
	else if (idx < snd_ecards_limit) {
		if (test_bit(idx, snd_cards_lock))
			err = -EBUSY;	/* invalid */
	} else if (idx >= SNDRV_CARDS)
		err = -ENODEV;
	if (err < 0) {
		mutex_unlock(&snd_card_mutex);
		dev_err(parent, "cannot find the slot for index %d (range 0-%i), error: %d\n",
			 idx, snd_ecards_limit - 1, err);
		kfree(card);
		return err;
	}
	set_bit(idx, snd_cards_lock);		/* lock it */
	if (idx >= snd_ecards_limit)
		snd_ecards_limit = idx + 1; /* increase the limit */
	mutex_unlock(&snd_card_mutex);
	card->dev = parent;
	card->number = idx;
	card->module = module;
	INIT_LIST_HEAD(&card->devices);
	init_rwsem(&card->controls_rwsem);
	rwlock_init(&card->ctl_files_rwlock);
	INIT_LIST_HEAD(&card->controls);
	INIT_LIST_HEAD(&card->ctl_files);
	spin_lock_init(&card->files_lock);
	INIT_LIST_HEAD(&card->files_list);
#ifdef CONFIG_PM
	init_waitqueue_head(&card->power_sleep);
#endif
	init_waitqueue_head(&card->remove_sleep);

	device_initialize(&card->card_dev);
	card->card_dev.parent = parent;
	card->card_dev.class = sound_class;
	card->card_dev.release = release_card_device;
	card->card_dev.groups = card->dev_groups;
	card->dev_groups[0] = &card_dev_attr_group;
	err = kobject_set_name(&card->card_dev.kobj, "card%d", idx);
	if (err < 0)
		goto __error;

	snprintf(card->irq_descr, sizeof(card->irq_descr), "%s:%s",
		 dev_driver_string(card->dev), dev_name(&card->card_dev));

	/* the control interface cannot be accessed from the user space until */
	/* snd_cards_bitmask and snd_cards are set with snd_card_register */
	err = snd_ctl_create(card);
	if (err < 0) {
		dev_err(parent, "unable to register control minors\n");
		goto __error;
	}
	err = snd_info_card_create(card);
	if (err < 0) {
		dev_err(parent, "unable to create card info\n");
		goto __error_ctl;
	}
	*card_ret = card;
	return 0;

      __error_ctl:
	snd_device_free_all(card);
      __error:
	put_device(&card->card_dev);
  	return err;
}