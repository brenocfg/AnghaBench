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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  IS_ARRAY 132 
#define  IS_DOUBLE 131 
#define  IS_LONG 130 
#define  IS_OBJECT 129 
#define  IS_STRING 128 
 double Z_DVAL_P (int /*<<< orphan*/ *) ; 
 double Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 unsigned short cluster_hash_key (char const*,int) ; 
 int snprintf (char*,int,char*,double) ; 

unsigned short cluster_hash_key_zval(zval *z_key) {
    const char *kptr;
    char buf[255];
    int klen;

    // Switch based on ZVAL type
    switch(Z_TYPE_P(z_key)) {
        case IS_STRING:
            kptr = Z_STRVAL_P(z_key);
            klen = Z_STRLEN_P(z_key);
            break;
        case IS_LONG:
            klen = snprintf(buf,sizeof(buf),"%ld",Z_LVAL_P(z_key));
            kptr = (const char *)buf;
            break;
        case IS_DOUBLE:
            klen = snprintf(buf,sizeof(buf),"%f",Z_DVAL_P(z_key));
            kptr = (const char *)buf;
            break;
        case IS_ARRAY:
            kptr = "Array";
            klen = sizeof("Array")-1;
            break;
        case IS_OBJECT:
            kptr = "Object";
            klen = sizeof("Object")-1;
            break;
        default:
            kptr = "";
            klen = 0;
    }

    // Hash the string representation
    return cluster_hash_key(kptr, klen);
}