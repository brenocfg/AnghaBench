#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int MaximumLength; scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_5__ {TYPE_1__ Str; int /*<<< orphan*/  FixedBuffer; } ;
typedef  TYPE_2__* PSDB_TMP_STR ;

/* Variables and functions */

void SdbpInitTempStr(PSDB_TMP_STR String)
{
    String->Str.Buffer = String->FixedBuffer;
    String->Str.Length = 0;
    String->Str.MaximumLength = sizeof(String->FixedBuffer);
}