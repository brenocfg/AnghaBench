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
typedef  int /*<<< orphan*/  xsltParserContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  const* CUR_PTR ; 
 scalar_t__ IS_COMBINING (int) ; 
 scalar_t__ IS_DIGIT (int) ; 
 scalar_t__ IS_EXTENDER (int) ; 
 scalar_t__ IS_LETTER (int) ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int xmlStringCurrentChar (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/ * xmlStrndup (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static xmlChar *
xsltScanNCName(xsltParserContextPtr ctxt) {
    const xmlChar *q, *cur;
    xmlChar *ret = NULL;
    int val, len;

    SKIP_BLANKS;

    cur = q = CUR_PTR;
    val = xmlStringCurrentChar(NULL, cur, &len);
    if (!IS_LETTER(val) && (val != '_'))
	return(NULL);

    while ((IS_LETTER(val)) || (IS_DIGIT(val)) ||
           (val == '.') || (val == '-') ||
	   (val == '_') ||
	   (IS_COMBINING(val)) ||
	   (IS_EXTENDER(val))) {
	cur += len;
	val = xmlStringCurrentChar(NULL, cur, &len);
    }
    ret = xmlStrndup(q, cur - q);
    CUR_PTR = cur;
    return(ret);
}