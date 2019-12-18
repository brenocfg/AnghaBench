#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* ptr; } ;
typedef  TYPE_1__ parser_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int tAND ; 
 int tCCValue ; 
 int tEQ ; 
 int tEQEQ ; 
 int tGEQ ; 
 int tLEQ ; 
 int tLSHIFT ; 
 int tNEQ ; 
 int tNEQEQ ; 
 int tOR ; 
 int tRRSHIFT ; 
 int tRSHIFT ; 
 int try_parse_ccval (TYPE_1__*,void*) ; 

__attribute__((used)) static int cc_parser_lex(void *lval, parser_ctx_t *ctx)
{
    int r;

    r = try_parse_ccval(ctx, lval);
    if(r)
        return r > 0 ? tCCValue : -1;

    switch(*ctx->ptr) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '~':
    case '%':
    case '^':
        return *ctx->ptr++;
    case '=':
         if(*++ctx->ptr == '=') {
             if(*++ctx->ptr == '=') {
                 ctx->ptr++;
                 return tEQEQ;
             }
             return tEQ;
         }
         break;
    case '!':
        if(*++ctx->ptr == '=') {
            if(*++ctx->ptr == '=') {
                ctx->ptr++;
                return tNEQEQ;
            }
            return tNEQ;
        }
        return '!';
    case '<':
        switch(*++ctx->ptr) {
        case '<':
            ctx->ptr++;
            return tLSHIFT;
        case '=':
            ctx->ptr++;
            return tLEQ;
        default:
            return '<';
        }
    case '>':
        switch(*++ctx->ptr) {
        case '>':
            if(*++ctx->ptr == '>') {
                ctx->ptr++;
                return tRRSHIFT;
            }
            return tRSHIFT;
        case '=':
            ctx->ptr++;
            return tGEQ;
        default:
            return '>';
        }
    case '|':
        if(*++ctx->ptr == '|') {
            ctx->ptr++;
            return tOR;
        }
        return '|';
    case '&':
        if(*++ctx->ptr == '&') {
            ctx->ptr++;
            return tAND;
        }
        return '&';
    }

    WARN("Failed to interpret %s\n", debugstr_w(ctx->ptr));
    return -1;
}