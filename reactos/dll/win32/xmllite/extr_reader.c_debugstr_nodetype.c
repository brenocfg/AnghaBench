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
typedef  size_t XmlNodeType ;

/* Variables and functions */
 size_t _XmlNodeType_Last ; 
 char const* wine_dbg_sprintf (char*,size_t) ; 

__attribute__((used)) static const char *debugstr_nodetype(XmlNodeType nodetype)
{
    static const char * const type_names[] =
    {
        "None",
        "Element",
        "Attribute",
        "Text",
        "CDATA",
        "",
        "",
        "ProcessingInstruction",
        "Comment",
        "",
        "DocumentType",
        "",
        "",
        "Whitespace",
        "",
        "EndElement",
        "",
        "XmlDeclaration"
    };

    if (nodetype > _XmlNodeType_Last)
        return wine_dbg_sprintf("unknown type=%d", nodetype);

    return type_names[nodetype];
}