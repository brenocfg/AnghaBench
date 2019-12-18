__attribute__((used)) static inline long os_atomic_load_long(const volatile long *ptr)
{
	return __atomic_load_n(ptr, __ATOMIC_SEQ_CST);
}