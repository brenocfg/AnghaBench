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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ php_com_dotnet_object ;
typedef  int STDAPI ;
typedef  int /*<<< orphan*/ * LPVARIANT ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 TYPE_1__* CDNO_FETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
#define  VARCMP_EQ 130 
#define  VARCMP_GT 129 
#define  VARCMP_LT 128 
 int /*<<< orphan*/  ZEND_COMPARE_OBJECTS_FALLBACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int com_objects_compare(zval *object1, zval *object2)
{
	php_com_dotnet_object *obja, *objb;
	int ret;
	/* strange header bug problem here... the headers define the proto without the
	 * flags parameter.  However, the MSDN docs state that there is a flags parameter,
	 * and my VC6 won't link unless the code uses the version with 4 parameters.
	 * So, we have this declaration here to fix it */
	STDAPI VarCmp(LPVARIANT pvarLeft, LPVARIANT pvarRight, LCID lcid, DWORD flags);

	ZEND_COMPARE_OBJECTS_FALLBACK(object1, object2);

	obja = CDNO_FETCH(object1);
	objb = CDNO_FETCH(object2);

	switch (VarCmp(&obja->v, &objb->v, LOCALE_SYSTEM_DEFAULT, 0)) {
		case VARCMP_LT:
			ret = -1;
			break;
		case VARCMP_GT:
			ret = 1;
			break;
		case VARCMP_EQ:
			ret = 0;
			break;
		default:
			/* either or both operands are NULL...
			 * not 100% sure how to handle this */
			ret = -2;
	}

	return ret;
}