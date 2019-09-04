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
struct TYPE_3__ {int valtype; } ;
typedef  TYPE_1__ OPTIONS ;

/* Variables and functions */

__attribute__((used)) static const char *valtype2param(const OPTIONS *o)
{
    switch (o->valtype) {
    case 0:
    case '-':
        return "";
    case 's':
        return "val";
    case '/':
        return "dir";
    case '<':
        return "infile";
    case '>':
        return "outfile";
    case 'p':
        return "+int";
    case 'n':
        return "int";
    case 'l':
        return "long";
    case 'u':
        return "ulong";
    case 'E':
        return "PEM|DER|ENGINE";
    case 'F':
        return "PEM|DER";
    case 'f':
        return "format";
    case 'M':
        return "intmax";
    case 'U':
        return "uintmax";
    }
    return "parm";
}