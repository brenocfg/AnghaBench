#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  TCCState ;

/* Variables and functions */
 TYPE_1__* file ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tcc_close () ; 
 int tcc_compile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcc_open_bf (int /*<<< orphan*/ *,char*,int) ; 

int tcc_compile_string(TCCState *s, const char *str)
{
	int len, ret;
	len = strlen (str);

	tcc_open_bf (s, "<string>", len);
	memcpy (file->buffer, str, len);
	ret = tcc_compile (s);
	tcc_close ();
	return ret;
}