#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ io; } ;
typedef  TYPE_1__ card_t ;

/* Variables and functions */
 scalar_t__ N2_PSR ; 
 int PSR_PAGEBITS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static __inline__ void openwin(card_t *card, u8 page)
{
	u8 psr = inb(card->io + N2_PSR);
	outb((psr & ~PSR_PAGEBITS) | page, card->io + N2_PSR);
}