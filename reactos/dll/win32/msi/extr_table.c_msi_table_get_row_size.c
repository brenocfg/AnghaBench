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
typedef  size_t UINT ;
struct TYPE_4__ {size_t offset; } ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  TYPE_1__ MSICOLUMNINFO ;

/* Variables and functions */
 size_t LONG_STR_BYTES ; 
 size_t bytes_per_column (int /*<<< orphan*/ *,TYPE_1__ const*,size_t) ; 

__attribute__((used)) static UINT msi_table_get_row_size( MSIDATABASE *db, const MSICOLUMNINFO *cols, UINT count, UINT bytes_per_strref )
{
    const MSICOLUMNINFO *last_col;

    if (!count)
        return 0;

    if (bytes_per_strref != LONG_STR_BYTES)
    {
        UINT i, size = 0;
        for (i = 0; i < count; i++) size += bytes_per_column( db, &cols[i], bytes_per_strref );
        return size;
    }
    last_col = &cols[count - 1];
    return last_col->offset + bytes_per_column( db, last_col, bytes_per_strref );
}