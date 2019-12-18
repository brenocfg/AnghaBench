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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/ * hfsplus_decompose_nonhangul (int /*<<< orphan*/ ,int*) ; 
 int hfsplus_try_decompose_hangul (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 *decompose_unichar(wchar_t uc, int *size, u16 *hangul_buffer)
{
	u16 *result;

	/* Hangul is handled separately */
	result = hangul_buffer;
	*size = hfsplus_try_decompose_hangul(uc, result);
	if (*size == 0)
		result = hfsplus_decompose_nonhangul(uc, size);
	return result;
}