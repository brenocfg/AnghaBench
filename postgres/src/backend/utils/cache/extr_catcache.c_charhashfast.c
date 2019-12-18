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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  murmurhash32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
charhashfast(Datum datum)
{
	return murmurhash32((int32) DatumGetChar(datum));
}