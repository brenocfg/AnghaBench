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
struct options {int /*<<< orphan*/  gc; scalar_t__ client_nat; } ;

/* Variables and functions */
 scalar_t__ new_client_nat_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cnol_check_alloc(struct options *options)
{
    if (!options->client_nat)
    {
        options->client_nat = new_client_nat_list(&options->gc);
    }
}