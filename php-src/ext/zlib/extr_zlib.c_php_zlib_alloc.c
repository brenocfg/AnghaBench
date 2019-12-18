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
typedef  int /*<<< orphan*/  voidpf ;
typedef  int /*<<< orphan*/  uInt ;

/* Variables and functions */
 int /*<<< orphan*/  safe_emalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static voidpf php_zlib_alloc(voidpf opaque, uInt items, uInt size)
{
	return (voidpf)safe_emalloc(items, size, 0);
}