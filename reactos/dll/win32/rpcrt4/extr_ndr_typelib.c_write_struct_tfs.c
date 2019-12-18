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
struct TYPE_4__ {int cbAlignment; int /*<<< orphan*/  cbSizeInstance; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;

/* Variables and functions */
 int FC_END ; 
 int FC_PAD ; 
 unsigned char FC_STRUCT ; 
 int /*<<< orphan*/  FIXME (char*,unsigned char) ; 
 int /*<<< orphan*/  WRITE_CHAR (unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  WRITE_SHORT (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 unsigned char get_struct_fc (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static size_t write_struct_tfs(ITypeInfo *typeinfo, unsigned char *str,
        size_t *len, TYPEATTR *attr)
{
    unsigned char fc = get_struct_fc(typeinfo, attr);
    size_t off = *len;

    if (fc != FC_STRUCT)
        FIXME("fc %02x not implemented\n", fc);

    WRITE_CHAR (str, *len, FC_STRUCT);
    WRITE_CHAR (str, *len, attr->cbAlignment - 1);
    WRITE_SHORT(str, *len, attr->cbSizeInstance);
    WRITE_CHAR (str, *len, FC_PAD);
    WRITE_CHAR (str, *len, FC_END);

    return off;
}