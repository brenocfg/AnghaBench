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
typedef  int /*<<< orphan*/  storage_number ;
typedef  double calculated_number ;

/* Variables and functions */
 int /*<<< orphan*/  SN_EXISTS ; 
 int /*<<< orphan*/  pack_storage_number (double,int /*<<< orphan*/ ) ; 
 double unpack_storage_number (int /*<<< orphan*/ ) ; 

calculated_number storage_number_min(calculated_number n) {
    calculated_number r = 1, last;

    do {
        last = n;
        n /= 2.0;
        storage_number t = pack_storage_number(n, SN_EXISTS);
        r = unpack_storage_number(t);
    } while(r != 0.0 && r != last);

    return last;
}