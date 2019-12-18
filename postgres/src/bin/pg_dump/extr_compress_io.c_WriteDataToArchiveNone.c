#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* writeF ) (int /*<<< orphan*/ *,char const*,size_t) ;} ;
typedef  TYPE_1__ CompressorState ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static void
WriteDataToArchiveNone(ArchiveHandle *AH, CompressorState *cs,
					   const char *data, size_t dLen)
{
	cs->writeF(AH, data, dLen);
	return;
}