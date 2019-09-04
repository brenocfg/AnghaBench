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
typedef  int /*<<< orphan*/  CGI_varlist ;

/* Variables and functions */
 int /*<<< orphan*/ * CGI_get_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CGI_get_post (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * CGI_get_query (int /*<<< orphan*/ *) ; 

CGI_varlist *
CGI_get_all(const char *template) {
    CGI_varlist *v = 0;

    v = CGI_get_cookie(v);
    v = CGI_get_query(v);
    v = CGI_get_post(v, template);
    return v;
}