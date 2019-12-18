#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* message_id; char* message; scalar_t__ domain; int /*<<< orphan*/  saved_errno; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  EVALUATE_MESSAGE (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ErrorContext ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  message ; 
 scalar_t__ save_format_domain ; 
 int /*<<< orphan*/  save_format_errnumber ; 

char *
format_elog_string(const char *fmt,...)
{
	ErrorData	errdata;
	ErrorData  *edata;
	MemoryContext oldcontext;

	/* Initialize a mostly-dummy error frame */
	edata = &errdata;
	MemSet(edata, 0, sizeof(ErrorData));
	/* the default text domain is the backend's */
	edata->domain = save_format_domain ? save_format_domain : PG_TEXTDOMAIN("postgres");
	/* set the errno to be used to interpret %m */
	edata->saved_errno = save_format_errnumber;

	oldcontext = MemoryContextSwitchTo(ErrorContext);

	edata->message_id = fmt;
	EVALUATE_MESSAGE(edata->domain, message, false, true);

	MemoryContextSwitchTo(oldcontext);

	return edata->message;
}