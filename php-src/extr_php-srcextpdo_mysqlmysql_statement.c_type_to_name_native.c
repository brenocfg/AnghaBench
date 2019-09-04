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

/* Variables and functions */
#define  FIELD_TYPE_BLOB 147 
#define  FIELD_TYPE_DATE 146 
#define  FIELD_TYPE_DATETIME 145 
#define  FIELD_TYPE_DECIMAL 144 
#define  FIELD_TYPE_DOUBLE 143 
#define  FIELD_TYPE_ENUM 142 
#define  FIELD_TYPE_FLOAT 141 
#define  FIELD_TYPE_INT24 140 
#define  FIELD_TYPE_LONG 139 
#define  FIELD_TYPE_LONGLONG 138 
#define  FIELD_TYPE_LONG_BLOB 137 
#define  FIELD_TYPE_MEDIUM_BLOB 136 
#define  FIELD_TYPE_NULL 135 
#define  FIELD_TYPE_SET 134 
#define  FIELD_TYPE_SHORT 133 
#define  FIELD_TYPE_STRING 132 
#define  FIELD_TYPE_TIME 131 
#define  FIELD_TYPE_TIMESTAMP 130 
#define  FIELD_TYPE_TINY_BLOB 129 
#define  FIELD_TYPE_VAR_STRING 128 

__attribute__((used)) static char *type_to_name_native(int type) /* {{{ */
{
#define PDO_MYSQL_NATIVE_TYPE_NAME(x)	case FIELD_TYPE_##x: return #x;

    switch (type) {
        PDO_MYSQL_NATIVE_TYPE_NAME(STRING)
        PDO_MYSQL_NATIVE_TYPE_NAME(VAR_STRING)
#ifdef FIELD_TYPE_TINY
        PDO_MYSQL_NATIVE_TYPE_NAME(TINY)
#endif
#ifdef FIELD_TYPE_BIT
        PDO_MYSQL_NATIVE_TYPE_NAME(BIT)
#endif
        PDO_MYSQL_NATIVE_TYPE_NAME(SHORT)
        PDO_MYSQL_NATIVE_TYPE_NAME(LONG)
        PDO_MYSQL_NATIVE_TYPE_NAME(LONGLONG)
        PDO_MYSQL_NATIVE_TYPE_NAME(INT24)
        PDO_MYSQL_NATIVE_TYPE_NAME(FLOAT)
        PDO_MYSQL_NATIVE_TYPE_NAME(DOUBLE)
        PDO_MYSQL_NATIVE_TYPE_NAME(DECIMAL)
#ifdef FIELD_TYPE_NEWDECIMAL
        PDO_MYSQL_NATIVE_TYPE_NAME(NEWDECIMAL)
#endif
#ifdef FIELD_TYPE_GEOMETRY
        PDO_MYSQL_NATIVE_TYPE_NAME(GEOMETRY)
#endif
        PDO_MYSQL_NATIVE_TYPE_NAME(TIMESTAMP)
#ifdef FIELD_TYPE_YEAR
        PDO_MYSQL_NATIVE_TYPE_NAME(YEAR)
#endif
        PDO_MYSQL_NATIVE_TYPE_NAME(SET)
        PDO_MYSQL_NATIVE_TYPE_NAME(ENUM)
        PDO_MYSQL_NATIVE_TYPE_NAME(DATE)
#ifdef FIELD_TYPE_NEWDATE
        PDO_MYSQL_NATIVE_TYPE_NAME(NEWDATE)
#endif
        PDO_MYSQL_NATIVE_TYPE_NAME(TIME)
        PDO_MYSQL_NATIVE_TYPE_NAME(DATETIME)
        PDO_MYSQL_NATIVE_TYPE_NAME(TINY_BLOB)
        PDO_MYSQL_NATIVE_TYPE_NAME(MEDIUM_BLOB)
        PDO_MYSQL_NATIVE_TYPE_NAME(LONG_BLOB)
        PDO_MYSQL_NATIVE_TYPE_NAME(BLOB)
        PDO_MYSQL_NATIVE_TYPE_NAME(NULL)
        default:
            return NULL;
    }
#undef PDO_MYSQL_NATIVE_TYPE_NAME
}