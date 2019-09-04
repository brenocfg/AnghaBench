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
typedef  void* xsltSecurityCheck ;
struct TYPE_3__ {void* writeNet; void* readNet; void* createDir; void* createFile; void* readFile; } ;

/* Variables and functions */
#define  XSLT_SECPREF_CREATE_DIRECTORY 132 
#define  XSLT_SECPREF_READ_FILE 131 
#define  XSLT_SECPREF_READ_NETWORK 130 
#define  XSLT_SECPREF_WRITE_FILE 129 
#define  XSLT_SECPREF_WRITE_NETWORK 128 
 int /*<<< orphan*/  xsltInitGlobals () ; 

int
xsltSetSecurityPrefs(xsltSecurityPrefsPtr sec, xsltSecurityOption option,
                     xsltSecurityCheck func) {
    xsltInitGlobals();
    if (sec == NULL)
	return(-1);
    switch (option) {
        case XSLT_SECPREF_READ_FILE:
            sec->readFile = func; return(0);
        case XSLT_SECPREF_WRITE_FILE:
            sec->createFile = func; return(0);
        case XSLT_SECPREF_CREATE_DIRECTORY:
            sec->createDir = func; return(0);
        case XSLT_SECPREF_READ_NETWORK:
            sec->readNet = func; return(0);
        case XSLT_SECPREF_WRITE_NETWORK:
            sec->writeNet = func; return(0);
    }
    return(-1);
}