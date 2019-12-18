__attribute__((used)) static inline void do_write(const volatile void *addr)
{
	int val = 0x1234567;

	asm volatile("stw %0,0(%1); sync; \n"
		     : : "r" (val), "r" (addr) : "memory");
}