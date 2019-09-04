#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jvmtiError ;
typedef  TYPE_1__* jvmtiEnv ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_9__ {scalar_t__ (* GetMethodDeclaringClass ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* GetSourceFileName ) (TYPE_1__**,int /*<<< orphan*/ ,char**) ;scalar_t__ (* GetClassSignature ) (TYPE_1__**,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Deallocate ) (TYPE_1__**,unsigned char*) ;} ;

/* Variables and functions */
 scalar_t__ JVMTI_ERROR_NONE ; 
 scalar_t__ JVMTI_ERROR_OUT_OF_MEMORY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  copy_class_filename (char*,char*,char*,int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  print_error (TYPE_1__**,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_1__**,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ stub3 (TYPE_1__**,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,unsigned char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,unsigned char*) ; 

__attribute__((used)) static jvmtiError
get_source_filename(jvmtiEnv *jvmti, jmethodID methodID, char ** buffer)
{
	jvmtiError ret;
	jclass decl_class;
	char *file_name = NULL;
	char *class_sign = NULL;
	char fn[PATH_MAX];
	size_t len;

	ret = (*jvmti)->GetMethodDeclaringClass(jvmti, methodID, &decl_class);
	if (ret != JVMTI_ERROR_NONE) {
		print_error(jvmti, "GetMethodDeclaringClass", ret);
		return ret;
	}

	ret = (*jvmti)->GetSourceFileName(jvmti, decl_class, &file_name);
	if (ret != JVMTI_ERROR_NONE) {
		print_error(jvmti, "GetSourceFileName", ret);
		return ret;
	}

	ret = (*jvmti)->GetClassSignature(jvmti, decl_class, &class_sign, NULL);
	if (ret != JVMTI_ERROR_NONE) {
		print_error(jvmti, "GetClassSignature", ret);
		goto free_file_name_error;
	}

	copy_class_filename(class_sign, file_name, fn, PATH_MAX);
	len = strlen(fn);
	*buffer = malloc((len + 1) * sizeof(char));
	if (!*buffer) {
		print_error(jvmti, "GetClassSignature", ret);
		ret = JVMTI_ERROR_OUT_OF_MEMORY;
		goto free_class_sign_error;
	}
	strcpy(*buffer, fn);
	ret = JVMTI_ERROR_NONE;

free_class_sign_error:
	(*jvmti)->Deallocate(jvmti, (unsigned char *)class_sign);
free_file_name_error:
	(*jvmti)->Deallocate(jvmti, (unsigned char *)file_name);

	return ret;
}