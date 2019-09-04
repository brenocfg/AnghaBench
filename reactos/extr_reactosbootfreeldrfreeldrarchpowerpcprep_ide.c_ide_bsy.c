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
struct TYPE_2__ {scalar_t__ port; } ;
typedef  TYPE_1__ idectl_desc ;

/* Variables and functions */
 int GetPhysByte (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sync () ; 

void ide_bsy( void *extension ) {
    idectl_desc *desc = (idectl_desc *)extension;
    while( GetPhysByte(desc->port+7) & 0x80 )
    {
    printf("Waiting for not busy\n");
    sync();
    }
}