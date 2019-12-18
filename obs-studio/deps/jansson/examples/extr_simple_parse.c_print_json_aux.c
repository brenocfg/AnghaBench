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
typedef  int /*<<< orphan*/  json_t ;

/* Variables and functions */
#define  JSON_ARRAY 135 
#define  JSON_FALSE 134 
#define  JSON_INTEGER 133 
#define  JSON_NULL 132 
#define  JSON_OBJECT 131 
#define  JSON_REAL 130 
#define  JSON_STRING 129 
#define  JSON_TRUE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int json_typeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_json_array (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_false (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_integer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_real (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_true (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

void print_json_aux(json_t *element, int indent) {
    switch (json_typeof(element)) {
    case JSON_OBJECT:
        print_json_object(element, indent);
        break;
    case JSON_ARRAY:
        print_json_array(element, indent);
        break;
    case JSON_STRING:
        print_json_string(element, indent);
        break;
    case JSON_INTEGER:
        print_json_integer(element, indent);
        break;
    case JSON_REAL:
        print_json_real(element, indent);
        break;
    case JSON_TRUE:
        print_json_true(element, indent);
        break;
    case JSON_FALSE:
        print_json_false(element, indent);
        break;
    case JSON_NULL:
        print_json_null(element, indent);
        break;
    default:
        fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
    }
}