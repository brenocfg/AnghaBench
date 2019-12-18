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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_ID_FULL_FONT_NAME ; 
 int /*<<< orphan*/  WARN (char*) ; 
 char* load_ttf_name_id (char const*,int /*<<< orphan*/ ) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *font_name_from_file( const WCHAR *filename )
{
    static const WCHAR truetypeW[] = {' ','(','T','r','u','e','T','y','p','e',')',0};
    WCHAR *name, *ret = NULL;

    if ((name = load_ttf_name_id( filename, NAME_ID_FULL_FONT_NAME )))
    {
        if (!name[0])
        {
            WARN("empty font name\n");
            msi_free( name );
            return NULL;
        }
        ret = msi_alloc( (strlenW( name ) + strlenW( truetypeW ) + 1 ) * sizeof(WCHAR) );
        strcpyW( ret, name );
        strcatW( ret, truetypeW );
        msi_free( name );
    }
    return ret;
}