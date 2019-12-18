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
struct grub_ntfs_file {scalar_t__ buf; TYPE_1__* data; } ;
struct grub_ntfs_attr {int /*<<< orphan*/ * sbuf; int /*<<< orphan*/  edat_buf; int /*<<< orphan*/  emft_buf; int /*<<< orphan*/  attr_end; scalar_t__ attr_nxt; int /*<<< orphan*/  flags; struct grub_ntfs_file* mft; } ;
struct TYPE_2__ {struct grub_ntfs_file mmft; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_MMFT ; 
 scalar_t__ u16at (scalar_t__,int) ; 

__attribute__((used)) static void
init_attr (struct grub_ntfs_attr *at, struct grub_ntfs_file *mft)
{
  at->mft = mft;
  at->flags = (mft == &mft->data->mmft) ? AF_MMFT : 0;
  at->attr_nxt = mft->buf + u16at (mft->buf, 0x14);
  at->attr_end = at->emft_buf = at->edat_buf = at->sbuf = NULL;
}