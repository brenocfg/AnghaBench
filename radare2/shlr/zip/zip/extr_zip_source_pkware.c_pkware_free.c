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
struct trad_pkware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct trad_pkware*) ; 

__attribute__((used)) static void
pkware_free(struct trad_pkware *ctx)
{
    free(ctx);
}