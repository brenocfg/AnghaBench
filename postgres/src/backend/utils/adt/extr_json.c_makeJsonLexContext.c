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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * makeJsonLexContextCstringLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

JsonLexContext *
makeJsonLexContext(text *json, bool need_escapes)
{
	return makeJsonLexContextCstringLen(VARDATA_ANY(json),
										VARSIZE_ANY_EXHDR(json),
										need_escapes);
}