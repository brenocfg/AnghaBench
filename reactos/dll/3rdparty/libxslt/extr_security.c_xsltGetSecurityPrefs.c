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
typedef  TYPE_1__* xsltSecurityPrefsPtr ;
typedef  int xsltSecurityOption ;
typedef  int /*<<< orphan*/ * xsltSecurityCheck ;
struct TYPE_3__ {int /*<<< orphan*/ * writeNet; int /*<<< orphan*/ * readNet; int /*<<< orphan*/ * createDir; int /*<<< orphan*/ * createFile; int /*<<< orphan*/ * readFile; } ;

/* Variables and functions */
#define  XSLT_SECPREF_CREATE_DIRECTORY 132 
#define  XSLT_SECPREF_READ_FILE 131 
#define  XSLT_SECPREF_READ_NETWORK 130 
#define  XSLT_SECPREF_WRITE_FILE 129 
#define  XSLT_SECPREF_WRITE_NETWORK 128 

xsltSecurityCheck
xsltGetSecurityPrefs(xsltSecurityPrefsPtr sec, xsltSecurityOption option) {
    if (sec == NULL)
	return(NULL);
    switch (option) {
        case XSLT_SECPREF_READ_FILE:
            return(sec->readFile);
        case XSLT_SECPREF_WRITE_FILE:
            return(sec->createFile);
        case XSLT_SECPREF_CREATE_DIRECTORY:
            return(sec->createDir);
        case XSLT_SECPREF_READ_NETWORK:
            return(sec->readNet);
        case XSLT_SECPREF_WRITE_NETWORK:
            return(sec->writeNet);
    }
    return(NULL);
}