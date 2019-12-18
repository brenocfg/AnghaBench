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
struct TYPE_3__ {char* ptr; char* end; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  int LONGLONG ;
typedef  int LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int INT_MAX ; 
 int MAXLONGLONG ; 
 scalar_t__ TRUE ; 
 scalar_t__ isdigitW (char) ; 
 scalar_t__ isinf (double) ; 
 int pow (int,int) ; 
 int tDouble ; 
 int tLong ; 
 int tShort ; 

__attribute__((used)) static int parse_numeric_literal(parser_ctx_t *ctx, void **ret)
{
    BOOL use_int = TRUE;
    LONGLONG d = 0, hlp;
    int exp = 0;
    double r;

    if(*ctx->ptr == '0' && !('0' <= ctx->ptr[1] && ctx->ptr[1] <= '9') && ctx->ptr[1] != '.')
        return *ctx->ptr++;

    while(ctx->ptr < ctx->end && isdigitW(*ctx->ptr)) {
        hlp = d*10 + *(ctx->ptr++) - '0';
        if(d>MAXLONGLONG/10 || hlp<0) {
            exp++;
            break;
        }
        else
            d = hlp;
    }
    while(ctx->ptr < ctx->end && isdigitW(*ctx->ptr)) {
        exp++;
        ctx->ptr++;
    }

    if(*ctx->ptr == '.') {
        use_int = FALSE;
        ctx->ptr++;

        while(ctx->ptr < ctx->end && isdigitW(*ctx->ptr)) {
            hlp = d*10 + *(ctx->ptr++) - '0';
            if(d>MAXLONGLONG/10 || hlp<0)
                break;

            d = hlp;
            exp--;
        }
        while(ctx->ptr < ctx->end && isdigitW(*ctx->ptr))
            ctx->ptr++;
    }

    if(*ctx->ptr == 'e' || *ctx->ptr == 'E') {
        int e = 0, sign = 1;

        if(*++ctx->ptr == '-') {
            ctx->ptr++;
            sign = -1;
        }

        if(!isdigitW(*ctx->ptr)) {
            FIXME("Invalid numeric literal\n");
            return 0;
        }

        use_int = FALSE;

        do {
            e = e*10 + *(ctx->ptr++) - '0';
            if(sign == -1 && -e+exp < -(INT_MAX/100)) {
                /* The literal will be rounded to 0 anyway. */
                while(isdigitW(*ctx->ptr))
                    ctx->ptr++;
                *(double*)ret = 0;
                return tDouble;
            }

            if(sign*e + exp > INT_MAX/100) {
                FIXME("Invalid numeric literal\n");
                return 0;
            }
        } while(isdigitW(*ctx->ptr));

        exp += sign*e;
    }

    if(use_int && (LONG)d == d) {
        LONG l = d;
        *(LONG*)ret = l;
        return (short)l == l ? tShort : tLong;
    }

    r = exp>=0 ? d*pow(10, exp) : d/pow(10, -exp);
    if(isinf(r)) {
        FIXME("Invalid numeric literal\n");
        return 0;
    }

    *(double*)ret = r;
    return tDouble;
}