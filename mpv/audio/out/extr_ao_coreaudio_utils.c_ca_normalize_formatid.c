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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ca_formatid_is_compressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioFormat60958AC3 ; 

__attribute__((used)) static uint32_t ca_normalize_formatid(uint32_t formatID)
{
    return ca_formatid_is_compressed(formatID) ? kAudioFormat60958AC3 : formatID;
}