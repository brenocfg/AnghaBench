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
typedef  scalar_t__ ZSTD_strategy ;
typedef  size_t U32 ;

/* Variables and functions */
 scalar_t__ ZSTD_btultra ; 

__attribute__((used)) static size_t ZSTD_minGain(size_t srcSize, ZSTD_strategy strat)
{
    U32 const minlog = (strat==ZSTD_btultra) ? 7 : 6;
    return (srcSize >> minlog) + 2;
}