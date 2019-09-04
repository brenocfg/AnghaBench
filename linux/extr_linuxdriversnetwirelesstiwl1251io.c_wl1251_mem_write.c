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
struct wl1251 {TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct wl1251*,int,void*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wl1251*,int,void*,size_t) ; 
 int wl1251_translate_mem_addr (struct wl1251*,int) ; 

void wl1251_mem_write(struct wl1251 *wl, int addr, void *buf, size_t len)
{
	int physical;

	physical = wl1251_translate_mem_addr(wl, addr);

	wl->if_ops->write(wl, physical, buf, len);
}