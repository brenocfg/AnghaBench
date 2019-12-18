#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_17__ {size_t propid; size_t dwOffset; } ;
struct TYPE_16__ {size_t cProperties; } ;
struct TYPE_11__ {int len; int /*<<< orphan*/  str; } ;
struct TYPE_13__ {int /*<<< orphan*/  i4; int /*<<< orphan*/  i2; int /*<<< orphan*/  ft; TYPE_1__ str; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  lVal; int /*<<< orphan*/  iVal; int /*<<< orphan*/  filetime; scalar_t__* pszVal; } ;
struct TYPE_14__ {scalar_t__ vt; TYPE_2__ u; } ;
typedef  TYPE_4__ PROPVARIANT ;
typedef  TYPE_5__ PROPERTY_DATA ;
typedef  TYPE_6__ PROPERTYSECTIONHEADER ;
typedef  TYPE_7__ PROPERTYIDOFFSET ;
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 size_t MSI_MAX_PROPS ; 
 size_t SECT_HDR_SIZE ; 
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_FILETIME ; 
 scalar_t__ VT_I2 ; 
 scalar_t__ VT_I4 ; 
 scalar_t__ VT_LPSTR ; 
 scalar_t__ get_type (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  propvar_changetype (TYPE_4__*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static void read_properties_from_data( PROPVARIANT *prop, LPBYTE data, DWORD sz )
{
    UINT type;
    DWORD i, size;
    PROPERTY_DATA *propdata;
    PROPVARIANT property, *ptr;
    PROPVARIANT changed;
    PROPERTYIDOFFSET *idofs;
    PROPERTYSECTIONHEADER *section_hdr;

    section_hdr = (PROPERTYSECTIONHEADER*) &data[0];
    idofs = (PROPERTYIDOFFSET*) &data[SECT_HDR_SIZE];

    /* now set all the properties */
    for( i = 0; i < section_hdr->cProperties; i++ )
    {
        if( idofs[i].propid >= MSI_MAX_PROPS )
        {
            ERR("Unknown property ID %d\n", idofs[i].propid );
            break;
        }

        type = get_type( idofs[i].propid );
        if( type == VT_EMPTY )
        {
            ERR("propid %d has unknown type\n", idofs[i].propid);
            break;
        }

        propdata = (PROPERTY_DATA*) &data[ idofs[i].dwOffset ];

        /* check we don't run off the end of the data */
        size = sz - idofs[i].dwOffset - sizeof(DWORD);
        if( sizeof(DWORD) > size ||
            ( propdata->type == VT_FILETIME && sizeof(FILETIME) > size ) ||
            ( propdata->type == VT_LPSTR && (propdata->u.str.len + sizeof(DWORD)) > size ) )
        {
            ERR("not enough data\n");
            break;
        }

        property.vt = propdata->type;
        if( propdata->type == VT_LPSTR )
        {
            LPSTR str = msi_alloc( propdata->u.str.len );
            memcpy( str, propdata->u.str.str, propdata->u.str.len );
            str[ propdata->u.str.len - 1 ] = 0;
            property.u.pszVal = str;
        }
        else if( propdata->type == VT_FILETIME )
            property.u.filetime = propdata->u.ft;
        else if( propdata->type == VT_I2 )
            property.u.iVal = propdata->u.i2;
        else if( propdata->type == VT_I4 )
            property.u.lVal = propdata->u.i4;

        /* check the type is the same as we expect */
        if( type != propdata->type )
        {
            propvar_changetype(&changed, &property, type);
            ptr = &changed;
        }
        else
            ptr = &property;

        prop[ idofs[i].propid ] = *ptr;
    }
}