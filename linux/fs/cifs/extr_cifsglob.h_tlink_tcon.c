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
struct tcon_link {struct cifs_tcon* tl_tcon; } ;
struct cifs_tcon {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cifs_tcon *
tlink_tcon(struct tcon_link *tlink)
{
	return tlink->tl_tcon;
}