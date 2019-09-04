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
struct ila_identifier {int /*<<< orphan*/  csum_neutral; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ila_csum_neutral_set(struct ila_identifier ident)
{
	return !!(ident.csum_neutral);
}