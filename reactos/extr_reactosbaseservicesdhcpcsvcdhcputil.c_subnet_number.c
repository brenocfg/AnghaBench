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
struct iaddr {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */

struct iaddr subnet_number( struct iaddr addr, struct iaddr mask ) {
    struct iaddr bcast = { 0 };
    return bcast;
}