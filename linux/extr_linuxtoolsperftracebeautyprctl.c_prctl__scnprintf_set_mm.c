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
typedef  int /*<<< orphan*/  DEFINE_STRARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  strarray__prctl_set_mm_options ; 
 size_t strarray__scnprintf (int /*<<< orphan*/ *,char*,size_t,char*,int) ; 

__attribute__((used)) static size_t prctl__scnprintf_set_mm(int option, char *bf, size_t size)
{
	static DEFINE_STRARRAY(prctl_set_mm_options);
	return strarray__scnprintf(&strarray__prctl_set_mm_options, bf, size, "%d", option);
}