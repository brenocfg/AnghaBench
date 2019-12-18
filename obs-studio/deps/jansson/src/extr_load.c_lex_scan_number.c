#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {double real; scalar_t__ integer; } ;
struct TYPE_14__ {int length; } ;
struct TYPE_13__ {int flags; TYPE_1__ value; int /*<<< orphan*/  token; TYPE_3__ saved_text; } ;
typedef  TYPE_2__ lex_t ;
typedef  scalar_t__ json_int_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int JSON_DECODE_INT_AS_REAL ; 
 int /*<<< orphan*/  TOKEN_INTEGER ; 
 int /*<<< orphan*/  TOKEN_INVALID ; 
 int /*<<< orphan*/  TOKEN_REAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_set (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ json_strtoint (char const*,char**,int) ; 
 scalar_t__ jsonp_strtod (TYPE_3__*,double*) ; 
 scalar_t__ l_isdigit (int) ; 
 int lex_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int lex_get_save (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_save (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lex_unget (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lex_unget_unsave (TYPE_2__*,int) ; 
 char* strbuffer_value (TYPE_3__*) ; 

__attribute__((used)) static int lex_scan_number(lex_t *lex, int c, json_error_t *error)
{
    const char *saved_text;
    char *end;
    double doubleval;

    lex->token = TOKEN_INVALID;

    if(c == '-')
        c = lex_get_save(lex, error);

    if(c == '0') {
        c = lex_get_save(lex, error);
        if(l_isdigit(c)) {
            lex_unget_unsave(lex, c);
            goto out;
        }
    }
    else if(l_isdigit(c)) {
        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }
    else {
        lex_unget_unsave(lex, c);
        goto out;
    }

    if(!(lex->flags & JSON_DECODE_INT_AS_REAL) &&
       c != '.' && c != 'E' && c != 'e')
    {
        json_int_t intval;

        lex_unget_unsave(lex, c);

        saved_text = strbuffer_value(&lex->saved_text);

        errno = 0;
        intval = json_strtoint(saved_text, &end, 10);
        if(errno == ERANGE) {
            if(intval < 0)
                error_set(error, lex, "too big negative integer");
            else
                error_set(error, lex, "too big integer");
            goto out;
        }

        assert(end == saved_text + lex->saved_text.length);

        lex->token = TOKEN_INTEGER;
        lex->value.integer = intval;
        return 0;
    }

    if(c == '.') {
        c = lex_get(lex, error);
        if(!l_isdigit(c)) {
            lex_unget(lex, c);
            goto out;
        }
        lex_save(lex, c);

        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }

    if(c == 'E' || c == 'e') {
        c = lex_get_save(lex, error);
        if(c == '+' || c == '-')
            c = lex_get_save(lex, error);

        if(!l_isdigit(c)) {
            lex_unget_unsave(lex, c);
            goto out;
        }

        do
            c = lex_get_save(lex, error);
        while(l_isdigit(c));
    }

    lex_unget_unsave(lex, c);

    if(jsonp_strtod(&lex->saved_text, &doubleval)) {
        error_set(error, lex, "real number overflow");
        goto out;
    }

    lex->token = TOKEN_REAL;
    lex->value.real = doubleval;
    return 0;

out:
    return -1;
}