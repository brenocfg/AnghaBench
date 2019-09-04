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
struct tape390_kekl {scalar_t__ type; scalar_t__ type_on_tape; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TAPE390_KEKL_TYPE_HASH ; 
 scalar_t__ TAPE390_KEKL_TYPE_LABEL ; 
 scalar_t__ TAPE390_KEKL_TYPE_NONE ; 

__attribute__((used)) static int check_ext_kekl(struct tape390_kekl *kekl)
{
	if (kekl->type == TAPE390_KEKL_TYPE_NONE)
		goto invalid;
	if (kekl->type > TAPE390_KEKL_TYPE_HASH)
		goto invalid;
	if (kekl->type_on_tape == TAPE390_KEKL_TYPE_NONE)
		goto invalid;
	if (kekl->type_on_tape > TAPE390_KEKL_TYPE_HASH)
		goto invalid;
	if ((kekl->type == TAPE390_KEKL_TYPE_HASH) &&
	    (kekl->type_on_tape == TAPE390_KEKL_TYPE_LABEL))
		goto invalid;

	return 0;
invalid:
	return -EINVAL;
}