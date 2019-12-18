#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {int nelts; TYPE_2__* elts; } ;
struct TYPE_10__ {TYPE_1__ args; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_MAIL_AUTH_CRAM_MD5 ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_EXTERNAL ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_LOGIN ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_LOGIN_USERNAME ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_PLAIN ; 
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int /*<<< orphan*/  ngx_mail_auth_external (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_mail_auth_plain (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_mail_starttls_only (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

ngx_int_t
ngx_mail_auth_parse(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t                 *arg;

#if (NGX_MAIL_SSL)
    if (ngx_mail_starttls_only(s, c)) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }
#endif

    if (s->args.nelts == 0) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    arg = s->args.elts;

    if (arg[0].len == 5) {

        if (ngx_strncasecmp(arg[0].data, (u_char *) "LOGIN", 5) == 0) {

            if (s->args.nelts == 1) {
                return NGX_MAIL_AUTH_LOGIN;
            }

            if (s->args.nelts == 2) {
                return NGX_MAIL_AUTH_LOGIN_USERNAME;
            }

            return NGX_MAIL_PARSE_INVALID_COMMAND;
        }

        if (ngx_strncasecmp(arg[0].data, (u_char *) "PLAIN", 5) == 0) {

            if (s->args.nelts == 1) {
                return NGX_MAIL_AUTH_PLAIN;
            }

            if (s->args.nelts == 2) {
                return ngx_mail_auth_plain(s, c, 1);
            }
        }

        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    if (arg[0].len == 8) {

        if (ngx_strncasecmp(arg[0].data, (u_char *) "CRAM-MD5", 8) == 0) {

            if (s->args.nelts != 1) {
                return NGX_MAIL_PARSE_INVALID_COMMAND;
            }

            return NGX_MAIL_AUTH_CRAM_MD5;
        }

        if (ngx_strncasecmp(arg[0].data, (u_char *) "EXTERNAL", 8) == 0) {

            if (s->args.nelts == 1) {
                return NGX_MAIL_AUTH_EXTERNAL;
            }

            if (s->args.nelts == 2) {
                return ngx_mail_auth_external(s, c, 1);
            }
        }

        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    return NGX_MAIL_PARSE_INVALID_COMMAND;
}