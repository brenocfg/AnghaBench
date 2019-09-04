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
typedef  enum operations { ____Placeholder_operations } operations ;
typedef  char WCHAR ;

/* Variables and functions */
#define  REG_ADD 137 
#define  REG_DELETE 136 
#define  REG_EXPORT 135 
#define  REG_IMPORT 134 
 int REG_INVALID ; 
#define  REG_QUERY 133 
#define  STRING_ADD_USAGE 132 
#define  STRING_DELETE_USAGE 131 
#define  STRING_EXPORT_USAGE 130 
#define  STRING_IMPORT_USAGE 129 
#define  STRING_QUERY_USAGE 128 
 int /*<<< orphan*/  lstrcmpiW (char const*,char const*) ; 

__attribute__((used)) static enum operations get_operation(const WCHAR *str, int *op_help)
{
    struct op_info { const WCHAR *op; int id; int help_id; };

    static const WCHAR add[] = {'a','d','d',0};
    static const WCHAR delete[] = {'d','e','l','e','t','e',0};
    static const WCHAR import[] = {'i','m','p','o','r','t',0};
    static const WCHAR export[] = {'e','x','p','o','r','t',0};
    static const WCHAR query[] = {'q','u','e','r','y',0};

    static const struct op_info op_array[] =
    {
        { add,     REG_ADD,     STRING_ADD_USAGE },
        { delete,  REG_DELETE,  STRING_DELETE_USAGE },
        { import,  REG_IMPORT,  STRING_IMPORT_USAGE },
        { export,  REG_EXPORT,  STRING_EXPORT_USAGE },
        { query,   REG_QUERY,   STRING_QUERY_USAGE },
        { NULL,    -1,          0 }
    };

    const struct op_info *ptr;

    for (ptr = op_array; ptr->op; ptr++)
    {
        if (!lstrcmpiW(str, ptr->op))
        {
            *op_help = ptr->help_id;
            return ptr->id;
        }
    }

    return REG_INVALID;
}