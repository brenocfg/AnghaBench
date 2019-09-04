#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  TYPE_1__* grub_dl_t ;
typedef  TYPE_2__* grub_dl_list_t ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__* mod; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_MODULE ; 
 int /*<<< orphan*/  GRUB_ERR_NONE ; 
 scalar_t__ grub_dl_get (int /*<<< orphan*/ ) ; 
 TYPE_2__* grub_dl_head ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ grub_malloc (int) ; 

grub_err_t
grub_dl_add (grub_dl_t mod)
{
  grub_dl_list_t l;

  if (grub_dl_get (mod->name))
    return grub_error (GRUB_ERR_BAD_MODULE,
		       "`%s' is already loaded", mod->name);

  l = (grub_dl_list_t) grub_malloc (sizeof (*l));
  if (! l)
    return grub_errno;

  l->mod = mod;
  l->next = grub_dl_head;
  grub_dl_head = l;

  return GRUB_ERR_NONE;
}