#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gbaudio_module_info {int /*<<< orphan*/  dev; } ;
struct gb_audio_enumerated {char* names; int /*<<< orphan*/  items; } ;
typedef  char __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char** devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char **gb_generate_enum_strings(struct gbaudio_module_info *gb,
					     struct gb_audio_enumerated *gbenum)
{
	const char **strings;
	int i;
	unsigned int items;
	__u8 *data;

	items = le32_to_cpu(gbenum->items);
	strings = devm_kcalloc(gb->dev, items, sizeof(char *), GFP_KERNEL);
	data = gbenum->names;

	for (i = 0; i < items; i++) {
		strings[i] = (const char *)data;
		while (*data != '\0')
			data++;
		data++;
	}

	return strings;
}