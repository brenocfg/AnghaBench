#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  vt; } ;
struct TYPE_8__ {size_t cDims; TYPE_1__* rgbounds; TYPE_3__ tdescElem; } ;
struct TYPE_7__ {int /*<<< orphan*/  cElements; } ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  TYPE_2__ ARRAYDESC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned char FC_EMBEDDED_COMPLEX ; 
 unsigned char FC_END ; 
 unsigned char FC_LGFARRAY ; 
 unsigned char FC_PAD ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  WRITE_CHAR (unsigned char*,size_t,unsigned char) ; 
 int /*<<< orphan*/  WRITE_INT (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_SHORT (unsigned char*,size_t,size_t) ; 
 unsigned char get_array_fc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 unsigned char get_base_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_memsize (int /*<<< orphan*/ *,TYPE_3__*) ; 
 size_t write_type_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t write_array_tfs(ITypeInfo *typeinfo, unsigned char *str,
    size_t *len, ARRAYDESC *desc)
{
    unsigned char fc = get_array_fc(typeinfo, &desc->tdescElem);
    ULONG size = type_memsize(typeinfo, &desc->tdescElem);
    unsigned char basetype;
    size_t ref = 0, off;
    USHORT i;

    if (fc != FC_LGFARRAY)
        FIXME("complex arrays not implemented\n");

    if (!(basetype = get_base_type(desc->tdescElem.vt)))
        ref = write_type_tfs(typeinfo, str, len, &desc->tdescElem, FALSE, FALSE);

    /* In theory arrays should be nested, but there's no reason not to marshal
     * [x][y] as [x*y]. */
    for (i = 0; i < desc->cDims; i++) size *= desc->rgbounds[i].cElements;

    off = *len;

    WRITE_CHAR(str, *len, FC_LGFARRAY);
    WRITE_CHAR(str, *len, 0);
    WRITE_INT (str, *len, size);
    if (basetype)
        WRITE_CHAR(str, *len, basetype);
    else
    {
        WRITE_CHAR (str, *len, FC_EMBEDDED_COMPLEX);
        WRITE_CHAR (str, *len, 0);
        WRITE_SHORT(str, *len, ref - *len);
        WRITE_CHAR (str, *len, FC_PAD);
    }
    WRITE_CHAR(str, *len, FC_END);

    return off;
}