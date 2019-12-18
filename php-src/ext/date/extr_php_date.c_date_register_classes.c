#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_handlers ;
struct TYPE_19__ {void* create_object; } ;
typedef  TYPE_1__ zend_class_entry ;
struct TYPE_22__ {int /*<<< orphan*/  write_property; int /*<<< orphan*/  read_property; void* get_gc; int /*<<< orphan*/  get_property_ptr_ptr; int /*<<< orphan*/  get_properties; void* clone_obj; int /*<<< orphan*/  free_obj; void* offset; void* compare; int /*<<< orphan*/  has_property; int /*<<< orphan*/  get_debug_info; void* get_properties_for; } ;
struct TYPE_21__ {int /*<<< orphan*/  get_iterator; } ;
struct TYPE_20__ {int /*<<< orphan*/  interface_gets_implemented; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_FORMAT_COOKIE ; 
 int /*<<< orphan*/  DATE_FORMAT_ISO8601 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC1036 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC1123 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC2822 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC3339 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC3339_EXTENDED ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC7231 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC822 ; 
 int /*<<< orphan*/  DATE_FORMAT_RFC850 ; 
 int /*<<< orphan*/  INIT_CLASS_ENTRY (TYPE_1__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_DATE_PERIOD_EXCLUDE_START_DATE ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_AFRICA ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ALL ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ALL_W_BC ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_AMERICA ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ANTARCTICA ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ARCTIC ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ASIA ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_ATLANTIC ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_AUSTRALIA ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_EUROPE ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_INDIAN ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_PACIFIC ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_GROUP_UTC ; 
 int /*<<< orphan*/  PHP_DATE_TIMEZONE_PER_COUNTRY ; 
 int /*<<< orphan*/  REGISTER_DATE_INTERFACE_CONST_STRING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGISTER_PERIOD_CLASS_CONST_STRING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGISTER_TIMEZONE_CLASS_CONST_STRING (char*,int /*<<< orphan*/ ) ; 
 void* XtOffsetOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* date_ce_date ; 
 TYPE_5__* date_ce_immutable ; 
 TYPE_2__* date_ce_interface ; 
 void* date_ce_interval ; 
 TYPE_5__* date_ce_period ; 
 void* date_ce_timezone ; 
 int /*<<< orphan*/  date_funcs_date ; 
 int /*<<< orphan*/  date_funcs_immutable ; 
 int /*<<< orphan*/  date_funcs_interface ; 
 int /*<<< orphan*/  date_funcs_interval ; 
 int /*<<< orphan*/  date_funcs_period ; 
 int /*<<< orphan*/  date_funcs_timezone ; 
 void* date_interval_compare_objects ; 
 int /*<<< orphan*/  date_interval_get_property_ptr_ptr ; 
 int /*<<< orphan*/  date_interval_has_property ; 
 int /*<<< orphan*/  date_interval_read_property ; 
 int /*<<< orphan*/  date_interval_write_property ; 
 void* date_object_clone_date ; 
 void* date_object_clone_interval ; 
 void* date_object_clone_period ; 
 void* date_object_clone_timezone ; 
 void* date_object_compare_date ; 
 int /*<<< orphan*/  date_object_free_storage_date ; 
 int /*<<< orphan*/  date_object_free_storage_interval ; 
 int /*<<< orphan*/  date_object_free_storage_period ; 
 int /*<<< orphan*/  date_object_free_storage_timezone ; 
 int /*<<< orphan*/  date_object_get_debug_info_timezone ; 
 void* date_object_get_gc ; 
 void* date_object_get_gc_interval ; 
 void* date_object_get_gc_period ; 
 void* date_object_get_gc_timezone ; 
 void* date_object_get_properties_for ; 
 void* date_object_get_properties_for_timezone ; 
 int /*<<< orphan*/  date_object_get_properties_interval ; 
 int /*<<< orphan*/  date_object_get_properties_period ; 
 TYPE_8__ date_object_handlers_date ; 
 TYPE_8__ date_object_handlers_immutable ; 
 TYPE_8__ date_object_handlers_interval ; 
 TYPE_8__ date_object_handlers_period ; 
 TYPE_8__ date_object_handlers_timezone ; 
 void* date_object_new_date ; 
 void* date_object_new_interval ; 
 void* date_object_new_period ; 
 void* date_object_new_timezone ; 
 int /*<<< orphan*/  date_object_period_get_iterator ; 
 int /*<<< orphan*/  date_period_get_property_ptr_ptr ; 
 int /*<<< orphan*/  date_period_read_property ; 
 int /*<<< orphan*/  date_period_write_property ; 
 int /*<<< orphan*/  implement_date_interface_handler ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_date_obj ; 
 int /*<<< orphan*/  php_interval_obj ; 
 int /*<<< orphan*/  php_period_obj ; 
 int /*<<< orphan*/  php_timezone_obj ; 
 int /*<<< orphan*/  std ; 
 int /*<<< orphan*/  std_object_handlers ; 
 TYPE_2__* zend_ce_traversable ; 
 int /*<<< orphan*/  zend_class_implements (TYPE_5__*,int,TYPE_2__*) ; 
 void* zend_register_internal_class_ex (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_register_internal_interface (TYPE_1__*) ; 

__attribute__((used)) static void date_register_classes(void) /* {{{ */
{
	zend_class_entry ce_date, ce_immutable, ce_timezone, ce_interval, ce_period, ce_interface;

	INIT_CLASS_ENTRY(ce_interface, "DateTimeInterface", date_funcs_interface);
	date_ce_interface = zend_register_internal_interface(&ce_interface);
	date_ce_interface->interface_gets_implemented = implement_date_interface_handler;

#define REGISTER_DATE_INTERFACE_CONST_STRING(const_name, value) \
	zend_declare_class_constant_stringl(date_ce_interface, const_name, sizeof(const_name)-1, value, sizeof(value)-1);

	REGISTER_DATE_INTERFACE_CONST_STRING("ATOM",             DATE_FORMAT_RFC3339);
	REGISTER_DATE_INTERFACE_CONST_STRING("COOKIE",           DATE_FORMAT_COOKIE);
	REGISTER_DATE_INTERFACE_CONST_STRING("ISO8601",          DATE_FORMAT_ISO8601);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC822",           DATE_FORMAT_RFC822);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC850",           DATE_FORMAT_RFC850);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC1036",          DATE_FORMAT_RFC1036);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC1123",          DATE_FORMAT_RFC1123);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC7231",          DATE_FORMAT_RFC7231);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC2822",          DATE_FORMAT_RFC2822);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC3339",          DATE_FORMAT_RFC3339);
	REGISTER_DATE_INTERFACE_CONST_STRING("RFC3339_EXTENDED", DATE_FORMAT_RFC3339_EXTENDED);
	REGISTER_DATE_INTERFACE_CONST_STRING("RSS",              DATE_FORMAT_RFC1123);
	REGISTER_DATE_INTERFACE_CONST_STRING("W3C",              DATE_FORMAT_RFC3339);

	INIT_CLASS_ENTRY(ce_date, "DateTime", date_funcs_date);
	ce_date.create_object = date_object_new_date;
	date_ce_date = zend_register_internal_class_ex(&ce_date, NULL);
	memcpy(&date_object_handlers_date, &std_object_handlers, sizeof(zend_object_handlers));
	date_object_handlers_date.offset = XtOffsetOf(php_date_obj, std);
	date_object_handlers_date.free_obj = date_object_free_storage_date;
	date_object_handlers_date.clone_obj = date_object_clone_date;
	date_object_handlers_date.compare = date_object_compare_date;
	date_object_handlers_date.get_properties_for = date_object_get_properties_for;
	date_object_handlers_date.get_gc = date_object_get_gc;
	zend_class_implements(date_ce_date, 1, date_ce_interface);

	INIT_CLASS_ENTRY(ce_immutable, "DateTimeImmutable", date_funcs_immutable);
	ce_immutable.create_object = date_object_new_date;
	date_ce_immutable = zend_register_internal_class_ex(&ce_immutable, NULL);
	memcpy(&date_object_handlers_immutable, &std_object_handlers, sizeof(zend_object_handlers));
	date_object_handlers_immutable.clone_obj = date_object_clone_date;
	date_object_handlers_immutable.compare = date_object_compare_date;
	date_object_handlers_immutable.get_properties_for = date_object_get_properties_for;
	date_object_handlers_immutable.get_gc = date_object_get_gc;
	zend_class_implements(date_ce_immutable, 1, date_ce_interface);

	INIT_CLASS_ENTRY(ce_timezone, "DateTimeZone", date_funcs_timezone);
	ce_timezone.create_object = date_object_new_timezone;
	date_ce_timezone = zend_register_internal_class_ex(&ce_timezone, NULL);
	memcpy(&date_object_handlers_timezone, &std_object_handlers, sizeof(zend_object_handlers));
	date_object_handlers_timezone.offset = XtOffsetOf(php_timezone_obj, std);
	date_object_handlers_timezone.free_obj = date_object_free_storage_timezone;
	date_object_handlers_timezone.clone_obj = date_object_clone_timezone;
	date_object_handlers_timezone.get_properties_for = date_object_get_properties_for_timezone;
	date_object_handlers_timezone.get_gc = date_object_get_gc_timezone;
	date_object_handlers_timezone.get_debug_info = date_object_get_debug_info_timezone;

#define REGISTER_TIMEZONE_CLASS_CONST_STRING(const_name, value) \
	zend_declare_class_constant_long(date_ce_timezone, const_name, sizeof(const_name)-1, value);

	REGISTER_TIMEZONE_CLASS_CONST_STRING("AFRICA",      PHP_DATE_TIMEZONE_GROUP_AFRICA);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("AMERICA",     PHP_DATE_TIMEZONE_GROUP_AMERICA);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ANTARCTICA",  PHP_DATE_TIMEZONE_GROUP_ANTARCTICA);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ARCTIC",      PHP_DATE_TIMEZONE_GROUP_ARCTIC);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ASIA",        PHP_DATE_TIMEZONE_GROUP_ASIA);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ATLANTIC",    PHP_DATE_TIMEZONE_GROUP_ATLANTIC);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("AUSTRALIA",   PHP_DATE_TIMEZONE_GROUP_AUSTRALIA);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("EUROPE",      PHP_DATE_TIMEZONE_GROUP_EUROPE);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("INDIAN",      PHP_DATE_TIMEZONE_GROUP_INDIAN);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("PACIFIC",     PHP_DATE_TIMEZONE_GROUP_PACIFIC);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("UTC",         PHP_DATE_TIMEZONE_GROUP_UTC);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ALL",         PHP_DATE_TIMEZONE_GROUP_ALL);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("ALL_WITH_BC", PHP_DATE_TIMEZONE_GROUP_ALL_W_BC);
	REGISTER_TIMEZONE_CLASS_CONST_STRING("PER_COUNTRY", PHP_DATE_TIMEZONE_PER_COUNTRY);

	INIT_CLASS_ENTRY(ce_interval, "DateInterval", date_funcs_interval);
	ce_interval.create_object = date_object_new_interval;
	date_ce_interval = zend_register_internal_class_ex(&ce_interval, NULL);
	memcpy(&date_object_handlers_interval, &std_object_handlers, sizeof(zend_object_handlers));
	date_object_handlers_interval.offset = XtOffsetOf(php_interval_obj, std);
	date_object_handlers_interval.free_obj = date_object_free_storage_interval;
	date_object_handlers_interval.clone_obj = date_object_clone_interval;
	date_object_handlers_interval.has_property = date_interval_has_property;
	date_object_handlers_interval.read_property = date_interval_read_property;
	date_object_handlers_interval.write_property = date_interval_write_property;
	date_object_handlers_interval.get_properties = date_object_get_properties_interval;
	date_object_handlers_interval.get_property_ptr_ptr = date_interval_get_property_ptr_ptr;
	date_object_handlers_interval.get_gc = date_object_get_gc_interval;
	date_object_handlers_interval.compare = date_interval_compare_objects;

	INIT_CLASS_ENTRY(ce_period, "DatePeriod", date_funcs_period);
	ce_period.create_object = date_object_new_period;
	date_ce_period = zend_register_internal_class_ex(&ce_period, NULL);
	date_ce_period->get_iterator = date_object_period_get_iterator;
	zend_class_implements(date_ce_period, 1, zend_ce_traversable);
	memcpy(&date_object_handlers_period, &std_object_handlers, sizeof(zend_object_handlers));
	date_object_handlers_period.offset = XtOffsetOf(php_period_obj, std);
	date_object_handlers_period.free_obj = date_object_free_storage_period;
	date_object_handlers_period.clone_obj = date_object_clone_period;
	date_object_handlers_period.get_properties = date_object_get_properties_period;
	date_object_handlers_period.get_property_ptr_ptr = date_period_get_property_ptr_ptr;
	date_object_handlers_period.get_gc = date_object_get_gc_period;
	date_object_handlers_period.read_property = date_period_read_property;
	date_object_handlers_period.write_property = date_period_write_property;

#define REGISTER_PERIOD_CLASS_CONST_STRING(const_name, value) \
	zend_declare_class_constant_long(date_ce_period, const_name, sizeof(const_name)-1, value);

	REGISTER_PERIOD_CLASS_CONST_STRING("EXCLUDE_START_DATE", PHP_DATE_PERIOD_EXCLUDE_START_DATE);
}