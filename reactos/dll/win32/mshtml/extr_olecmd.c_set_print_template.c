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
typedef  int /*<<< orphan*/  nstemplate ;
typedef  int /*<<< orphan*/  nsIPrintSettings ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  scalar_t__ PRUnichar ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  GetLocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  set_head_text (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlenW (scalar_t__*) ; 

__attribute__((used)) static void set_print_template(nsIPrintSettings *settings, LPCWSTR template, BOOL head)
{
    PRUnichar nstemplate[200]; /* FIXME: Use dynamic allocation */
    PRUnichar *p = nstemplate;
    LPCWSTR ptr=template;
    int pos=0;

    while(*ptr) {
        if(*ptr != '&') {
            *p++ = *ptr++;
            continue;
        }

        switch(*++ptr) {
        case '&':
            *p++ = '&';
            *p++ = '&';
            ptr++;
            break;
        case 'b': /* change align */
            ptr++;
            *p = 0;
            set_head_text(settings, nstemplate, head, pos);
            p = nstemplate;
            pos++;
            break;
        case 'd': { /* short date */
            SYSTEMTIME systime;
            GetLocalTime(&systime);
            GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &systime, NULL, p,
                    sizeof(nstemplate)-(p-nstemplate)*sizeof(WCHAR));
            p += strlenW(p);
            ptr++;
            break;
        }
        case 'p': /* page number */
            *p++ = '&';
            *p++ = 'P';
            ptr++;
            break;
        case 'P': /* page count */
            *p++ = '?'; /* FIXME */
            ptr++;
            break;
        case 'u':
            *p++ = '&';
            *p++ = 'U';
            ptr++;
            break;
        case 'w':
            /* FIXME: set window title */
            ptr++;
            break;
        default:
            *p++ = '&';
            *p++ = *ptr++;
        }
    }

    *p = 0;
    set_head_text(settings, nstemplate, head, pos);

    while(++pos < 3)
        set_head_text(settings, p, head, pos);
}