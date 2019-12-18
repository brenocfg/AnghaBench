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
typedef  int _u32 ;
typedef  int /*<<< orphan*/  _sblock ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * sflash_block_name ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void print_block_name (_u32 ublock) {
    char _sblock[4];
    snprintf (_sblock, sizeof(_sblock), "%03u", ublock);
    memcpy (&sflash_block_name[2], _sblock, 3);
}