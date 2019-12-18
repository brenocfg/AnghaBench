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
struct compressionParameters {int /*<<< orphan*/  LZ4_dictStreamHC; int /*<<< orphan*/  LZ4_streamHC; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_freeStreamHC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LZ4_compressCleanupStreamHC(
    const struct compressionParameters* pThis)
{
    LZ4_freeStreamHC(pThis->LZ4_streamHC);
    LZ4_freeStreamHC(pThis->LZ4_dictStreamHC);
}