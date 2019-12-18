#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 

__attribute__((used)) static void
AddAcl(PQExpBuffer aclbuf, const char *keyword, const char *subname)
{
	if (aclbuf->len > 0)
		appendPQExpBufferChar(aclbuf, ',');
	appendPQExpBufferStr(aclbuf, keyword);
	if (subname)
		appendPQExpBuffer(aclbuf, "(%s)", subname);
}