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
typedef  int /*<<< orphan*/  pgssSharedState ;
typedef  int /*<<< orphan*/  pgssEntry ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  MAXALIGN (int) ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_estimate_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgss_max ; 

__attribute__((used)) static Size
pgss_memsize(void)
{
	Size		size;

	size = MAXALIGN(sizeof(pgssSharedState));
	size = add_size(size, hash_estimate_size(pgss_max, sizeof(pgssEntry)));

	return size;
}