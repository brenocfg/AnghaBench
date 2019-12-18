#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* zend_off_t ;
struct TYPE_7__ {int fp_type; size_t manifest_pos; TYPE_1__* phar; void* offset; int /*<<< orphan*/  is_persistent; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_8__ {int fp_type; void* offset; } ;
typedef  TYPE_3__ phar_entry_fp_info ;
typedef  enum phar_fp_type { ____Placeholder_phar_fp_type } phar_fp_type ;
struct TYPE_9__ {TYPE_3__* manifest; } ;
struct TYPE_6__ {size_t phar_pos; } ;

/* Variables and functions */
 TYPE_5__* PHAR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cached_fp ; 

__attribute__((used)) static inline void phar_set_fp_type(phar_entry_info *entry, enum phar_fp_type type, zend_off_t offset)
{
	phar_entry_fp_info *data;

	if (!entry->is_persistent) {
		entry->fp_type = type;
		entry->offset = offset;
		return;
	}
	data = &(PHAR_G(cached_fp)[entry->phar->phar_pos].manifest[entry->manifest_pos]);
	data->fp_type = type;
	data->offset = offset;
}