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
typedef  int /*<<< orphan*/  u32 ;
struct audit_field {int dummy; } ;
struct TYPE_2__ {struct audit_field* fields; } ;
struct audit_entry {TYPE_1__ rule; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct audit_field* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct audit_entry*) ; 
 struct audit_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct audit_entry *audit_init_entry(u32 field_count)
{
	struct audit_entry *entry;
	struct audit_field *fields;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (unlikely(!entry))
		return NULL;

	fields = kcalloc(field_count, sizeof(*fields), GFP_KERNEL);
	if (unlikely(!fields)) {
		kfree(entry);
		return NULL;
	}
	entry->rule.fields = fields;

	return entry;
}