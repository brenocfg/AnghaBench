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
typedef  TYPE_1__* xsltParserContextPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_3__ {int error; } ;

/* Variables and functions */
 char CUR ; 
 int /*<<< orphan*/  const* CUR_PTR ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  SKIP_BLANKS ; 
 int xmlStringCurrentChar (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/ * xmlStrndup (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static xmlChar *
xsltScanLiteral(xsltParserContextPtr ctxt) {
    const xmlChar *q, *cur;
    xmlChar *ret = NULL;
    int val, len;

    SKIP_BLANKS;
    if (CUR == '"') {
        NEXT;
	cur = q = CUR_PTR;
	val = xmlStringCurrentChar(NULL, cur, &len);
	while ((IS_CHAR(val)) && (val != '"')) {
	    cur += len;
	    val = xmlStringCurrentChar(NULL, cur, &len);
	}
	if (!IS_CHAR(val)) {
	    ctxt->error = 1;
	    return(NULL);
	} else {
	    ret = xmlStrndup(q, cur - q);
        }
	cur += len;
	CUR_PTR = cur;
    } else if (CUR == '\'') {
        NEXT;
	cur = q = CUR_PTR;
	val = xmlStringCurrentChar(NULL, cur, &len);
	while ((IS_CHAR(val)) && (val != '\'')) {
	    cur += len;
	    val = xmlStringCurrentChar(NULL, cur, &len);
	}
	if (!IS_CHAR(val)) {
	    ctxt->error = 1;
	    return(NULL);
	} else {
	    ret = xmlStrndup(q, cur - q);
        }
	cur += len;
	CUR_PTR = cur;
    } else {
	/* XP_ERROR(XPATH_START_LITERAL_ERROR); */
	ctxt->error = 1;
	return(NULL);
    }
    return(ret);
}