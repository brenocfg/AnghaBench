#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tb_property_entry {int length; int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;
typedef  struct tb_property_entry u32 ;
struct tb_property_dir {int dummy; } ;
struct TYPE_2__ {char* data; char* text; int /*<<< orphan*/  immediate; struct tb_property_dir* dir; } ;
struct tb_property {int length; int type; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TB_PROPERTY_KEY_SIZE ; 
#define  TB_PROPERTY_TYPE_DATA 131 
#define  TB_PROPERTY_TYPE_DIRECTORY 130 
#define  TB_PROPERTY_TYPE_TEXT 129 
 int TB_PROPERTY_TYPE_UNKNOWN ; 
#define  TB_PROPERTY_TYPE_VALUE 128 
 struct tb_property_dir* __tb_property_parse_dir (struct tb_property_entry const*,size_t,int /*<<< orphan*/ ,int,int) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tb_property*) ; 
 int /*<<< orphan*/  parse_dwdata (char*,struct tb_property_entry const*,int) ; 
 struct tb_property* tb_property_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_property_entry_valid (struct tb_property_entry const*,size_t) ; 

__attribute__((used)) static struct tb_property *tb_property_parse(const u32 *block, size_t block_len,
					const struct tb_property_entry *entry)
{
	char key[TB_PROPERTY_KEY_SIZE + 1];
	struct tb_property *property;
	struct tb_property_dir *dir;

	if (!tb_property_entry_valid(entry, block_len))
		return NULL;

	parse_dwdata(key, entry, 2);
	key[TB_PROPERTY_KEY_SIZE] = '\0';

	property = tb_property_alloc(key, entry->type);
	if (!property)
		return NULL;

	property->length = entry->length;

	switch (property->type) {
	case TB_PROPERTY_TYPE_DIRECTORY:
		dir = __tb_property_parse_dir(block, block_len, entry->value,
					      entry->length, false);
		if (!dir) {
			kfree(property);
			return NULL;
		}
		property->value.dir = dir;
		break;

	case TB_PROPERTY_TYPE_DATA:
		property->value.data = kcalloc(property->length, sizeof(u32),
					       GFP_KERNEL);
		if (!property->value.data) {
			kfree(property);
			return NULL;
		}
		parse_dwdata(property->value.data, block + entry->value,
			     entry->length);
		break;

	case TB_PROPERTY_TYPE_TEXT:
		property->value.text = kcalloc(property->length, sizeof(u32),
					       GFP_KERNEL);
		if (!property->value.text) {
			kfree(property);
			return NULL;
		}
		parse_dwdata(property->value.text, block + entry->value,
			     entry->length);
		/* Force null termination */
		property->value.text[property->length * 4 - 1] = '\0';
		break;

	case TB_PROPERTY_TYPE_VALUE:
		property->value.immediate = entry->value;
		break;

	default:
		property->type = TB_PROPERTY_TYPE_UNKNOWN;
		break;
	}

	return property;
}