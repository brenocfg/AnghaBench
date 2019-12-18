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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_dlm_byCopy ; 
 size_t ZSTD_estimateCDictSize_advanced (size_t,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_getCParams (int,int /*<<< orphan*/ ,size_t) ; 

size_t ZSTD_estimateCDictSize(size_t dictSize, int compressionLevel)
{
    ZSTD_compressionParameters const cParams = ZSTD_getCParams(compressionLevel, 0, dictSize);
    return ZSTD_estimateCDictSize_advanced(dictSize, cParams, ZSTD_dlm_byCopy);
}