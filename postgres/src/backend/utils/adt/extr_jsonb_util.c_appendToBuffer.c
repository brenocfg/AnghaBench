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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  copyToBuffer (int /*<<< orphan*/ ,int,char const*,int) ; 
 int reserveFromBuffer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
appendToBuffer(StringInfo buffer, const char *data, int len)
{
	int			offset;

	offset = reserveFromBuffer(buffer, len);
	copyToBuffer(buffer, offset, data, len);
}