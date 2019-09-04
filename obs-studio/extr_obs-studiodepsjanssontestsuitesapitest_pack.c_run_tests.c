#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {size_t refcount; } ;
typedef  TYPE_1__ json_t ;
typedef  int /*<<< orphan*/  json_int_t ;
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_error (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  fail (char*) ; 
 TYPE_1__* json_array_get (TYPE_1__*,int) ; 
 int json_array_size (TYPE_1__*) ; 
 int /*<<< orphan*/  json_decref (TYPE_1__*) ; 
 int /*<<< orphan*/  json_integer (int) ; 
 int json_integer_value (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_array (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_false (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_integer (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_null (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_object (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_real (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_string (TYPE_1__*) ; 
 int /*<<< orphan*/  json_is_true (TYPE_1__*) ; 
 TYPE_1__* json_object_get (TYPE_1__*,char*) ; 
 int json_object_size (TYPE_1__*) ; 
 TYPE_1__* json_pack (char*,...) ; 
 scalar_t__ json_pack_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 double json_real_value (TYPE_1__*) ; 
 int /*<<< orphan*/  json_string_value (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_tests()
{
    json_t *value;
    int i;
    char buffer[4] = {'t', 'e', 's', 't'};
    json_error_t error;

    /*
     * Simple, valid json_pack cases
     */
    /* true */
    value = json_pack("b", 1);
    if(!json_is_true(value))
        fail("json_pack boolean failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack boolean refcount failed");
    json_decref(value);

    /* false */
    value = json_pack("b", 0);
    if(!json_is_false(value))
        fail("json_pack boolean failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack boolean refcount failed");
    json_decref(value);

    /* null */
    value = json_pack("n");
    if(!json_is_null(value))
        fail("json_pack null failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack null refcount failed");
    json_decref(value);

    /* integer */
    value = json_pack("i", 1);
    if(!json_is_integer(value) || json_integer_value(value) != 1)
        fail("json_pack integer failed");
    if(value->refcount != (size_t)1)
        fail("json_pack integer refcount failed");
    json_decref(value);

    /* integer from json_int_t */
    value = json_pack("I", (json_int_t)555555);
    if(!json_is_integer(value) || json_integer_value(value) != 555555)
        fail("json_pack json_int_t failed");
    if(value->refcount != (size_t)1)
        fail("json_pack integer refcount failed");
    json_decref(value);

    /* real */
    value = json_pack("f", 1.0);
    if(!json_is_real(value) || json_real_value(value) != 1.0)
        fail("json_pack real failed");
    if(value->refcount != (size_t)1)
        fail("json_pack real refcount failed");
    json_decref(value);

    /* string */
    value = json_pack("s", "test");
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string refcount failed");
    json_decref(value);

    /* nullable string (defined case) */
    value = json_pack("s?", "test");
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack nullable string (defined case) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack nullable string (defined case) refcount failed");
    json_decref(value);

    /* nullable string (NULL case) */
    value = json_pack("s?", NULL);
    if(!json_is_null(value))
        fail("json_pack nullable string (NULL case) failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack nullable string (NULL case) refcount failed");
    json_decref(value);

    /* string and length (int) */
    value = json_pack("s#", "test asdf", 4);
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string and length failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string and length refcount failed");
    json_decref(value);

    /* string and length (size_t) */
    value = json_pack("s%", "test asdf", (size_t)4);
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string and length failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string and length refcount failed");
    json_decref(value);

    /* string and length (int), non-NUL terminated string */
    value = json_pack("s#", buffer, 4);
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string and length (int) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string and length (int) refcount failed");
    json_decref(value);

    /* string and length (size_t), non-NUL terminated string */
    value = json_pack("s%", buffer, (size_t)4);
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string and length (size_t) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string and length (size_t) refcount failed");
    json_decref(value);

    /* string concatenation */
    value = json_pack("s++", "te", "st", "ing");
    if(!json_is_string(value) || strcmp("testing", json_string_value(value)))
        fail("json_pack string concatenation failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string concatenation refcount failed");
    json_decref(value);

    /* string concatenation and length (int) */
    value = json_pack("s#+#+", "test", 1, "test", 2, "test");
    if(!json_is_string(value) || strcmp("ttetest", json_string_value(value)))
        fail("json_pack string concatenation and length (int) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string concatenation and length (int) refcount failed");
    json_decref(value);

    /* string concatenation and length (size_t) */
    value = json_pack("s%+%+", "test", (size_t)1, "test", (size_t)2, "test");
    if(!json_is_string(value) || strcmp("ttetest", json_string_value(value)))
        fail("json_pack string concatenation and length (size_t) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack string concatenation and length (size_t) refcount failed");
    json_decref(value);

    /* empty object */
    value = json_pack("{}", 1.0);
    if(!json_is_object(value) || json_object_size(value) != 0)
        fail("json_pack empty object failed");
    if(value->refcount != (size_t)1)
        fail("json_pack empty object refcount failed");
    json_decref(value);

    /* empty list */
    value = json_pack("[]", 1.0);
    if(!json_is_array(value) || json_array_size(value) != 0)
        fail("json_pack empty list failed");
    if(value->refcount != (size_t)1)
        fail("json_pack empty list failed");
    json_decref(value);

    /* non-incref'd object */
    value = json_pack("o", json_integer(1));
    if(!json_is_integer(value) || json_integer_value(value) != 1)
        fail("json_pack object failed");
    if(value->refcount != (size_t)1)
        fail("json_pack integer refcount failed");
    json_decref(value);

    /* non-incref'd nullable object (defined case) */
    value = json_pack("o?", json_integer(1));
    if(!json_is_integer(value) || json_integer_value(value) != 1)
        fail("json_pack nullable object (defined case) failed");
    if(value->refcount != (size_t)1)
        fail("json_pack nullable object (defined case) refcount failed");
    json_decref(value);

    /* non-incref'd nullable object (NULL case) */
    value = json_pack("o?", NULL);
    if(!json_is_null(value))
        fail("json_pack nullable object (NULL case) failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack nullable object (NULL case) refcount failed");
    json_decref(value);

    /* incref'd object */
    value = json_pack("O", json_integer(1));
    if(!json_is_integer(value) || json_integer_value(value) != 1)
        fail("json_pack object failed");
    if(value->refcount != (size_t)2)
        fail("json_pack integer refcount failed");
    json_decref(value);
    json_decref(value);

    /* incref'd nullable object (defined case) */
    value = json_pack("O?", json_integer(1));
    if(!json_is_integer(value) || json_integer_value(value) != 1)
        fail("json_pack incref'd nullable object (defined case) failed");
    if(value->refcount != (size_t)2)
        fail("json_pack incref'd nullable object (defined case) refcount failed");
    json_decref(value);
    json_decref(value);

    /* incref'd nullable object (NULL case) */
    value = json_pack("O?", NULL);
    if(!json_is_null(value))
        fail("json_pack incref'd nullable object (NULL case) failed");
    if(value->refcount != (size_t)-1)
        fail("json_pack incref'd nullable object (NULL case) refcount failed");

    /* simple object */
    value = json_pack("{s:[]}", "foo");
    if(!json_is_object(value) || json_object_size(value) != 1)
        fail("json_pack array failed");
    if(!json_is_array(json_object_get(value, "foo")))
        fail("json_pack array failed");
    if(json_object_get(value, "foo")->refcount != (size_t)1)
        fail("json_pack object refcount failed");
    json_decref(value);

    /* object with complex key */
    value = json_pack("{s+#+: []}", "foo", "barbar", 3, "baz");
    if(!json_is_object(value) || json_object_size(value) != 1)
        fail("json_pack array failed");
    if(!json_is_array(json_object_get(value, "foobarbaz")))
        fail("json_pack array failed");
    if(json_object_get(value, "foobarbaz")->refcount != (size_t)1)
        fail("json_pack object refcount failed");
    json_decref(value);

    /* simple array */
    value = json_pack("[i,i,i]", 0, 1, 2);
    if(!json_is_array(value) || json_array_size(value) != 3)
        fail("json_pack object failed");
    for(i=0; i<3; i++)
    {
        if(!json_is_integer(json_array_get(value, i)) ||
           json_integer_value(json_array_get(value, i)) != i)

            fail("json_pack integer array failed");
    }
    json_decref(value);

    /* Whitespace; regular string */
    value = json_pack(" s ", "test");
    if(!json_is_string(value) || strcmp("test", json_string_value(value)))
        fail("json_pack string (with whitespace) failed");
    json_decref(value);

    /* Whitespace; empty array */
    value = json_pack("[ ]");
    if(!json_is_array(value) || json_array_size(value) != 0)
        fail("json_pack empty array (with whitespace) failed");
    json_decref(value);

    /* Whitespace; array */
    value = json_pack("[ i , i,  i ] ", 1, 2, 3);
    if(!json_is_array(value) || json_array_size(value) != 3)
        fail("json_pack array (with whitespace) failed");
    json_decref(value);

    /*
     * Invalid cases
     */

    /* newline in format string */
    if(json_pack_ex(&error, 0, "{\n\n1"))
        fail("json_pack failed to catch invalid format '1'");
    check_error("Expected format 's', got '1'", "<format>", 3, 1, 4);

    /* mismatched open/close array/object */
    if(json_pack_ex(&error, 0, "[}"))
        fail("json_pack failed to catch mismatched '}'");
    check_error("Unexpected format character '}'", "<format>", 1, 2, 2);

    if(json_pack_ex(&error, 0, "{]"))
        fail("json_pack failed to catch mismatched ']'");
    check_error("Expected format 's', got ']'", "<format>", 1, 2, 2);

    /* missing close array */
    if(json_pack_ex(&error, 0, "["))
        fail("json_pack failed to catch missing ']'");
    check_error("Unexpected end of format string", "<format>", 1, 2, 2);

    /* missing close object */
    if(json_pack_ex(&error, 0, "{"))
        fail("json_pack failed to catch missing '}'");
    check_error("Unexpected end of format string", "<format>", 1, 2, 2);

    /* garbage after format string */
    if(json_pack_ex(&error, 0, "[i]a", 42))
        fail("json_pack failed to catch garbage after format string");
    check_error("Garbage after format string", "<format>", 1, 4, 4);

    if(json_pack_ex(&error, 0, "ia", 42))
        fail("json_pack failed to catch garbage after format string");
    check_error("Garbage after format string", "<format>", 1, 2, 2);

    /* NULL string */
    if(json_pack_ex(&error, 0, "s", NULL))
        fail("json_pack failed to catch null argument string");
    check_error("NULL string argument", "<args>", 1, 1, 1);

    /* + on its own */
    if(json_pack_ex(&error, 0, "+", NULL))
        fail("json_pack failed to a lone +");
    check_error("Unexpected format character '+'", "<format>", 1, 1, 1);

    /* NULL format */
    if(json_pack_ex(&error, 0, NULL))
        fail("json_pack failed to catch NULL format string");
    check_error("NULL or empty format string", "<format>", -1, -1, 0);

    /* NULL key */
    if(json_pack_ex(&error, 0, "{s:i}", NULL, 1))
        fail("json_pack failed to catch NULL key");
    check_error("NULL string argument", "<args>", 1, 2, 2);

    /* More complicated checks for row/columns */
    if(json_pack_ex(&error, 0, "{ {}: s }", "foo"))
        fail("json_pack failed to catch object as key");
    check_error("Expected format 's', got '{'", "<format>", 1, 3, 3);

    /* Complex object */
    if(json_pack_ex(&error, 0, "{ s: {},  s:[ii{} }", "foo", "bar", 12, 13))
        fail("json_pack failed to catch missing ]");
    check_error("Unexpected format character '}'", "<format>", 1, 19, 19);

    /* Complex array */
    if(json_pack_ex(&error, 0, "[[[[[   [[[[[  [[[[ }]]]] ]]]] ]]]]]"))
        fail("json_pack failed to catch extra }");
    check_error("Unexpected format character '}'", "<format>", 1, 21, 21);

    /* Invalid UTF-8 in object key */
    if(json_pack_ex(&error, 0, "{s:i}", "\xff\xff", 42))
        fail("json_pack failed to catch invalid UTF-8 in an object key");
    check_error("Invalid UTF-8 object key", "<args>", 1, 2, 2);

    /* Invalid UTF-8 in a string */
    if(json_pack_ex(&error, 0, "{s:s}", "foo", "\xff\xff"))
        fail("json_pack failed to catch invalid UTF-8 in a string");
    check_error("Invalid UTF-8 string", "<args>", 1, 4, 4);
}