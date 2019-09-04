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
typedef  int /*<<< orphan*/  u8 ;
struct bq4802 {scalar_t__ ioport; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static u8 bq4802_read_io(struct bq4802 *p, int off)
{
	return inb(p->ioport + off);
}