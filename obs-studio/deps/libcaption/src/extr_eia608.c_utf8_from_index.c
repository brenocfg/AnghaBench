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

/* Variables and functions */
 int EIA608_CHAR_COUNT ; 
 char const** eia608_char_map ; 

__attribute__((used)) static const char* utf8_from_index(int idx) { return (0 <= idx && EIA608_CHAR_COUNT > idx) ? eia608_char_map[idx] : ""; }